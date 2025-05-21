//#pragma once
//
//#include "GameInstance.h"
////boost
//#include <boost/beast/core.hpp>
//#include <boost/beast/http.hpp>
//#include <boost/beast/version.hpp>
//#include <boost/asio/connect.hpp>
//#include <boost/asio/ip/tcp.hpp>
//#include <nlohmann/json.hpp>
//namespace beast = boost::beast;
//namespace http = beast::http;
//namespace net = boost::asio;
//using tcp = net::ip::tcp;
//using json = nlohmann::json;
//#include "nlohmann/json.hpp"
//
//BEGIN(Engine)
//
//
//class CNetwork_Manager final : public CBase
//{
//private:
//	CNetwork_Manager();
//	virtual ~CNetwork_Manager() = default;
//
//public:
//	HRESULT Initialize();
//
//public:
//	string	Ping();
//
//
//private:
//	json SendHttpGetJson(const string& host, const string& port, const string& target);
//
//public:
//	static CNetwork_Manager* Create();
//	virtual void Free() override;
//
//};
//
//END