#ifndef __IEGAD_REDIS_KEY__
#define __IEGAD_REDIS_KEY__


#include "iegad_redis_command.hpp"


namespace iegad {
namespace redis {
        

class key_t : public command {
public:
    typedef std::shared_ptr<key_t> ptr_t;


    static ptr_t Create(connection & conn) {
        ptr_t p(new key_t(conn));
        return p;
    }


    virtual ~key_t() {}


    int64_t del(const std::string & __key_) {
        this->make_cmdstr("DEL ", { __key_ });
        return this->action_number();
    }


    const std::string dump(const std::string & __key_) {
        this->make_cmdstr("DUMP ", { __key_ });
        return this->action_string();
    }


    int64_t exists(const std::string & __key_) {
        this->make_cmdstr("EXISTS ", { __key_ });
        return this->action_number();
    }


    int64_t expire(const std::string & __key_, uint64_t time_in_sec) {
        this->make_cmdstr("EXPIRE ", { __key_, std::to_string(time_in_sec) });
        return this->action_number();
    }


    int64_t expireat(const std::string & __key_, uint64_t unix_timestamp) {
        this->make_cmdstr("EXPIREAT ", { __key_, std::to_string(unix_timestamp) });
        return this->action_number();
    }


    int64_t pexpire(const std::string & __key_, uint64_t milliseconds) {
        this->make_cmdstr("PEXPIRE ", { __key_, std::to_string(milliseconds) });
        return this->action_number();
    }


    int64_t pexpireat(const std::string & __key_, uint64_t milliseconds) {
        this->make_cmdstr("PEXPIREAT ", { __key_, " ", std::to_string(milliseconds) });
        return this->action_number();
    }


    const std::vector<std::string> keys(const std::string & pattern) {
        this->make_cmdstr("KEYS ", { pattern });
        return this->action_vector();
    }


    int64_t move(const std::string & __key_, int db) {
        this->make_cmdstr("MOVE ", { __key_, std::to_string(db) });
        return this->action_number();
    }


    int64_t persist(const std::string & __key_) {
        this->make_cmdstr("PERSIST ", { __key_ });
        return this->action_number();
    }


    int64_t pttl(const std::string & __key_) {
        this->make_cmdstr("PTTL ", { __key_ });
        return this->action_number();
    }


    int64_t ttl(const std::string & __key_) {
        this->make_cmdstr("TTL ", { __key_ });
        return this->action_number();
    }


    const std::string randomkey() {
        this->make_cmdstr("RANDOMKEY ", {});
        return this->action_string();
    }


    bool rename(const std::string & __key_, const std::string & newname,
                std::string * errstr = nullptr) {
        this->make_cmdstr("RENAME ", { __key_, newname });
        return this->action_status(errstr);
    }


    bool renamenx(const std::string & __key_, const std::string & newname,
                  std::string * errstr = nullptr) {
        this->make_cmdstr("RENAMENX ", { __key_, newname });
        return this->action_status(errstr);
    }


    const std::string type(const std::string & __key_) {
        this->make_cmdstr("TYPE ", { __key_ });
        return this->action_string();
    }


private:
    explicit key_t(connection & conn)
        :
    command(conn) {}
}; // class key_t;


} // namespace redis_ex;
} // namespace iegad;


#endif // __IEGAD_REDIS_KEY__;
