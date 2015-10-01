#include <boost/asio.hpp>


#include <iostream>
#include "tcp_mt_server.h"
#include "job_worker.hpp"
#include "iegad_log.h"
#include "echo_svc.h"



using namespace iegad::common;


/* ===================================
@ 说明 :

  整个程序的在vs2013 的配置下, 字符集选用 unicode编码方式所以, 
  所有的字符串都必需使用 std::wstring类型, 目的是为了正确的传输
  中文;

  在使用 protocol buffer 的传输时, 应将 std::wstring 转换成为utf8
  编码格式.

  在日志类的构造函数中, 会将当前字符集初始为 "chs(简体中文)";

 =================================== */


int 
main(int argc, char * argv[])
{
    iegad::common::_LOG log(argv[0]);
    std::shared_ptr<iegad::net::echo_svc> echo_svc_(new iegad::net::echo_svc(10));
    std::cout << echo_svc_->get_id();


    iegad::net::tcp_mt_svr host("127.0.0.1", 6688);
    host.regist_svc(echo_svc_);
    host.run(1);


    std::cout << "done" << std::endl;
    std::cin.get();
    exit(0);
}
