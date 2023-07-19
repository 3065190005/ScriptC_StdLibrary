#include "SelectClass.h"

SelectClass::tagUnit_type SelectClass::initUnit(SOCKET socket)
{
    tagUnit_type ret;
    ret.socket = socket;
    return ret;
}

bool SelectClass::Join(tagUnit_type& sock)
{
    if (sock.state == tagUnit_state::is_set)
        return true;

    if (sock.socket <= 0)
        return false;

    tagElement_type * element = nullptr;
    auto finder = m_element.begin();

    for (; finder!=m_element.end() ; finder++)
    {
        if (finder->count == FD_SETSIZE)
            continue;
        element = &*finder;
        break;
    }

    if (finder == m_element.end()) 
    {
        m_element.push_back(tagElement_type());
        element = &m_element.back();
    }

    if (element)
    {
        sock.fd = &element->fd;
        sock.state = tagUnit_state::is_set;

        FD_SET(sock.socket, sock.fd);
        element->count += 1;
 
        return true;
    }
    else
    {
        return false;
    }
}

bool SelectClass::Leave(tagUnit_type& sock)
{
    if (sock.state == tagUnit_state::no_set)
        return true;

    if (sock.fd == nullptr)
        return false;

    for (auto& i : m_element) {
        if (FD_ISSET(sock.socket, &i.fd))
        {
            i.count -= 1;
        }
    }

    FD_CLR(sock.socket, sock.fd);

    
    sock.state = tagUnit_state::no_set;
    sock.fd = nullptr;

    return true;
}

SelectClass::select_ret SelectClass::Select(std::list<tagUnit_type> sockets,struct timeval tv)
{
    SelectClass::select_ret ret;

    unit_list read_sock;
    unit_list write_sock;
    unit_list error_sock;

    fd_set_list read_list(1);
    fd_set_list write_list(1);
    fd_set_list error_list(1);

    FD_ZERO(&read_list.back());
    FD_ZERO(&write_list.back());
    FD_ZERO(&error_list.back());

    int count = 0;

    for (auto& i : sockets)
    {
        if (i.state != tagUnit_state::is_set)
            continue;

        if (count == FD_SETSIZE)
        {
            read_list.push_back(fd_set());
            write_list.push_back(fd_set());
            error_list.push_back(fd_set());

            FD_ZERO(&read_list.back());
            FD_ZERO(&write_list.back());
            FD_ZERO(&error_list.back());
            count = 0;
        }

        FD_SET(i.socket, &read_list.back());
        FD_SET(i.socket, &write_list.back());
        FD_SET(i.socket, &error_list.back());

        count++;
    }

    auto read_iter = read_list.begin();
    auto write_iter = write_list.begin();
    auto error_iter = error_list.begin();

    for (auto i = 0; i < read_list.size(); i++)
    {        
        int result = ::select(0, &*read_iter, &*write_iter, &*error_iter, &tv);
        if (result == SOCKET_ERROR)
        {
            std::get<3>(ret) = -1;
            return std::move(ret);
        }

        for (auto& i : sockets) {
            if (FD_ISSET(i.socket, &*read_iter)) {
                read_sock.push_back(i);
            }

            if (FD_ISSET(i.socket, &*write_iter)) {
                write_sock.push_back(i);
            }

            if (FD_ISSET(i.socket, &*error_iter)) {
                error_sock.push_back(i);
            }
        }

        read_iter++;
        write_iter++;
        error_iter++;
    }

    std::get<0>(ret) = std::move(read_sock);
    std::get<1>(ret) = std::move(write_sock);
    std::get<2>(ret) = std::move(error_sock);
    std::get<3>(ret) = 0;

    return std::move(ret);
}
