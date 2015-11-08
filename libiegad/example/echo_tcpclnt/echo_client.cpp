#include <iostream>
#include "nets/basic_proxy.h"
#include "iegad_define.h"
#include <thread>




#ifdef WIN32
#pragma comment(lib, "libiegad_netc.lib")
#pragma comment(lib, "libiegad_common.lib")
#pragma comment(lib, "libiegad_msg.lib")
#pragma comment(lib, "libglog.lib")
#pragma comment(lib, "libprotobuf.lib")
#endif // WIN32




class echo_proxy : public iegad::netc::basic_proxy {
public:
    echo_proxy(const std::string & host, const std::string & svc) 
	: iegad::netc::basic_proxy(host, svc) {}


    virtual const std::string call(const std::string & msgstr) override {
	boost::system::error_code err_code;
	if (this->_connect() != 0) {
	    return ERR_STRING;
	}
	if (this->_send_basic_msg(10, 10, msgstr, err_code) != 0 && err_code) {
	    std::cout << err_code.message() << std::endl;
	    return ERR_STRING;
	}
	std::string res = this->_recv(err_code);	
	if (err_code) {
	    std::cout << err_code.message() << std::endl;
	}
	return res;
    }
};


class echoEx_proxy : public iegad::netc::basic_proxy {
public:
    echoEx_proxy(const std::string & host, const std::string & svc)
	: iegad::netc::basic_proxy(host, svc) {}


    virtual const std::string call(const std::string & msgstr) override {
	boost::system::error_code err_code;
	if (this->_connect() != 0) {
	    return ERR_STRING;
	}
	if (this->_send_basic_msg(11, 10, msgstr, err_code) != 0 && err_code) {
	    std::cout << err_code.message() << std::endl;
	    return ERR_STRING;
	}
	iegad::msg::basic_msg msgbsc;
	if (this->_recv_basic_msg(msgbsc, err_code) != 0 && err_code) {
	    std::cout << err_code.message() << std::endl;
	    return ERR_STRING;
	}
	return msgbsc.msg_bdstr();
    }
};


enum {
    NTIME = 10
};


void 
thread_proc()
{
    echo_proxy echoPrx("127.0.0.1", "6688");
    echoEx_proxy echoExPrc("127.0.0.1", "6688");
    std::string msgstr = "1234567890";
    for (int i = 0; i < NTIME; i++) {
	if (echoPrx.call(msgstr) == ERR_STRING) {
	    std::cout << "call failed" << std::endl;
	}
	echoPrx.close();
	std::cout << echoExPrc.call(msgstr) << std::endl;
	echoExPrc.close();
    }
}


int 
main(int argc, char * argv[])
{
    while (true) {
	std::vector<std::thread> thread_pool;
	for (int i = 0; i < NTIME; i++) {
	    thread_pool.push_back(std::move(std::thread(thread_proc)));
	}

	for (int i = 0; i < NTIME; i++) {
	    thread_pool[i].join();
	}

	std::this_thread::sleep_for(std::chrono::seconds(5));
    }


    std::cout << "done" << std::endl;
    std::cin.get();
    exit(0);
}