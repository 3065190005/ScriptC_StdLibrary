#include "DllFuncReader.h"
#include "QuickLib/quicklib.h"

#include <direct.h>

using namespace Cervice::Obj;

#define IoS "io__"
#define OsS "os__"
#define MathS "math__"
#define StrS "str__"
#define VecS "vec__"
#define TimS "time__"
#define TypS "type__"
#define WindowS "fltk_window__"
#define ThreadS "thread__"
#define SocketS "socket__"

#define func(var,va2)( "__system__" va2 var "__")

template<typename... Args>
void s_call(std::string name, auto_c* ret, Args... Ts) {
    DllFuncReader* manager = DllFuncReader::getInstance();
    auto func = manager->getFuncFromDll(name.c_str());
    std::vector<auto_c> param;
    auto space = { (param.push_back(Ts),0)... };
    manager->callFunc(func, &param, ret);
}


void ServerTcp(int args, char** argv)
{
    DllFuncReader* manager = DllFuncReader::getInstance();
    auto func = manager->getFuncFromDll("__system___setArgv__");
    manager->callFunc(func, (std::vector<auto_c>*)argv, (auto_c*)&args);

    auto_c family, type, address, port, listen_count, client_socket, send_buf, send_lens, recv_len, space;
    auto_c socket_id, bind_result, listen_result, accept_count, send_result, recv_result, close_result;

    family << AF_INET;
    type << SOCK_STREAM;
    address << "127.0.0.1";
    port << 8099;
    listen_count << 10;
    send_buf << "Server";
    send_lens << (numberT)strnlen_s("Server", 100);

    recv_len << 100;

    s_call(func("socket_create", SocketS), &socket_id, family, type);
    s_call(func("socket_bind", SocketS), &bind_result, socket_id, address, port);
    s_call(func("socket_listen", SocketS), &listen_result, socket_id, listen_count);
    s_call(func("socket_accept", SocketS), &accept_count, socket_id);

    if (accept_count.getType() == LetObject::ObjT::array)
    {
        client_socket = accept_count[0];

        s_call(func("socket_send", SocketS), &send_result, client_socket, send_buf, send_lens);
        std::cout << "send_lens : " << LetObject::cast<numberT>(send_result) << std::endl;
        s_call(func("socket_recv", SocketS), &recv_result, client_socket, recv_len);

        if(recv_result.getType() == LetObject::ObjT::string)
            std::cout << "recv_lens : " << LetObject::cast<std::string>(recv_result) << std::endl;
        else
            std::cout << "recv error id  : " << LetObject::cast<numberT>(recv_result) << std::endl;

        s_call(func("socket_close", SocketS), &close_result, client_socket);
    }

    s_call(func("socket_close", SocketS), &close_result, socket_id);
}


void ClientTcp(int args, char** argv)
{
    DllFuncReader* manager = DllFuncReader::getInstance();
    auto func = manager->getFuncFromDll("__system___setArgv__");
    manager->callFunc(func, (std::vector<auto_c>*)argv, (auto_c*)&args);

    auto_c family, type, address, port, listen_count, client_socket, send_buf, send_lens, recv_len, space;
    auto_c socket_id, connect_result, listen_result, accept_count, send_result, recv_result, close_result;

    family << AF_INET;
    type << SOCK_STREAM;
    address << "127.0.0.1";
    port << 8099;

    send_buf << "Server";
    send_lens << (numberT)strnlen_s("Server", 100);

    recv_len << 100;

    s_call(func("socket_create", SocketS), &socket_id, family, type);

    s_call(func("socket_connect", SocketS), &connect_result, socket_id, address, port);

    s_call(func("socket_send", SocketS), &send_result, socket_id, send_buf, send_lens);
    std::cout << "send_lens : " << LetObject::cast<numberT>(send_result) << std::endl;
    s_call(func("socket_recv", SocketS), &recv_result, socket_id, recv_len);

    if (recv_result.getType() == LetObject::ObjT::string)
        std::cout << "recv_lens : " << LetObject::cast<std::string>(recv_result) << std::endl;
    else
        std::cout << "recv error id  : " << LetObject::cast<numberT>(recv_result) << std::endl;

    s_call(func("socket_close", SocketS), &close_result, socket_id);
}


void ServerUdp(int args, char** argv)
{
    DllFuncReader* manager = DllFuncReader::getInstance();
    auto func = manager->getFuncFromDll("__system___setArgv__");
    manager->callFunc(func, (std::vector<auto_c>*)argv, (auto_c*)&args);

    auto_c family, type, address, port, listen_count, client_socket, send_buf, send_lens, recv_len, space;
    auto_c socket_id, bind_result, listen_result, send_port, send_result, recv_result, close_result;

    family << AF_INET;
    type << SOCK_DGRAM;
    address << "127.0.0.1";
    port << 9096;
    listen_count << 10;
    send_buf << "Server";
    send_lens << (numberT)strnlen_s("Server", 100);
    send_port << 9097;
    recv_len << 100;

    s_call(func("socket_create", SocketS), &socket_id, family, type);
    s_call(func("socket_bind", SocketS), &bind_result, socket_id, address, port);

    s_call(func("socket_sendto", SocketS), &send_result, socket_id, send_buf, send_lens, address, send_port);

    std::cout << "sendto_lens : " << LetObject::cast<numberT>(send_result) << std::endl;
    
    s_call(func("socket_recvfrom", SocketS), &recv_result, socket_id, recv_len);

    if (recv_result.getType() == LetObject::ObjT::array) 
    {
        std::cout << "recvfrom_lens : " << LetObject::cast<std::string>(recv_result[0]) << std::endl;
    }
    else
        std::cout << "recv error id  : " << LetObject::cast<numberT>(recv_result) << std::endl;

    s_call(func("socket_close", SocketS), &close_result, socket_id);
}

void SelectTcp(int args, char** argv)
{
    DllFuncReader* manager = DllFuncReader::getInstance();
    auto func = manager->getFuncFromDll("__system___setArgv__");
    manager->callFunc(func, (std::vector<auto_c>*)argv, (auto_c*)&args);

    auto_c family, type, address, port, listen_count, client_socket, send_buf, send_lens, recv_len, select_list, wait_time;
    auto_c socket_id, bind_result, listen_result, accept_count, send_result, recv_result, close_result, select_reuslt;

    family << AF_INET;
    type << SOCK_STREAM;
    address << "127.0.0.1";
    port << 7077;
    listen_count << 10;
    send_buf << "Server";
    send_lens << (numberT)strnlen_s("Server", 100)+1;

    recv_len << 100;

    wait_time << 6300;

    s_call(func("socket_create", SocketS), &socket_id, family, type);
    s_call(func("socket_bind", SocketS), &bind_result, socket_id, address, port);
    s_call(func("socket_listen", SocketS), &listen_result, socket_id, listen_count);

    select_list[0] = socket_id;
    while (true)
    {
        bool coni = false;
        s_call(func("socket_select", SocketS), &select_reuslt, select_list, wait_time);

        for (auto& i : select_reuslt.getNumArray())
        {
            auto element = i.second.getStrArray();
            if (element.find("r") != element.end())
            {
                coni = true;
                break;
            }
        }

        if (coni == false)
        {
            std::cout << "no socket connect " << std::endl;
            continue;
        }
        else {
            s_call(func("socket_accept", SocketS), &accept_count, socket_id);

            if (accept_count.getType() == LetObject::ObjT::array)
            {
                client_socket = accept_count[0];

                s_call(func("socket_send", SocketS), &send_result, client_socket, send_buf, send_lens);
                std::cout << "send_lens : " << LetObject::cast<numberT>(send_result) << std::endl;
                s_call(func("socket_recv", SocketS), &recv_result, client_socket, recv_len);

                if (recv_result.getType() == LetObject::ObjT::string)
                    std::cout << "recv_lens : " << LetObject::cast<std::string>(recv_result) << std::endl;
                else
                    std::cout << "recv error id  : " << LetObject::cast<numberT>(recv_result) << std::endl;

                s_call(func("socket_close", SocketS), &close_result, client_socket);
            }
        }
    }
    s_call(func("socket_close", SocketS), &close_result, socket_id);
}

int main(int args , char** argv)
{
    DllFuncReader* manager = DllFuncReader::getInstance();
    auto func = manager->getFuncFromDll("__system___setArgv__");
    manager->callFunc(func, (std::vector<auto_c>*)argv, (auto_c*)&args);

    auto_c hostName, hostIp,released;

    while (true) {
        SelectTcp(args, argv);
    }
    return 0;
}


/*
* 基础标准库
* std_io "io" 输入输出库                    √
* std_os "os" 系统库                     √
* std_math "math" 数学库                   √
* std_string "string" 字符串处理库        √
* std_array  "array"  数组处理库         √  
* std_time "time" 时间库               √                    
* std_type "type" 类型库               √
* 
* -- maybe
* 高级标准库
* std_window "window" 窗口库           √
* std_thread "thread" 线程库           √
* std_direct "direct" 目录库
* std_regex "regex" 正则库
* std_socket "socket" 网络库
*/


/*
* 
*/