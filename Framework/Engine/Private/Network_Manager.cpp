//#include "NetWork_Manager.h"
//
//
//CNetwork_Manager::CNetwork_Manager()
//{
//}
//
//HRESULT CNetwork_Manager::Initialize()
//{
//
//	return S_OK;
//}
//
//string CNetwork_Manager::Ping()
//{
//    std::string host = "localhost";
//    std::string port = "8080";
//    std::string target = "/ping";
//
//    json j = SendHttpGetJson(host, port, target);
//
//    // JSON 객체처럼 사용 가능
//    std::cout << "title: " << j["title"] << std::endl;
//    std::cout << "userId: " << j["userId"] << std::endl;
//
//    return 0;
//}
//
//json CNetwork_Manager::SendHttpGetJson(const string& host, const string& port, const string& target)
//{
//    try {
//        net::io_context ioc;
//        tcp::resolver resolver(ioc);
//        beast::tcp_stream stream(ioc);
//
//        auto const results = resolver.resolve(host, port);
//        stream.connect(results);
//
//        http::request<http::string_body> req{ http::verb::get, target, 11 };
//        req.set(http::field::host, host);
//        req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);
//
//        http::write(stream, req);
//
//        beast::flat_buffer buffer;
//        http::response<http::dynamic_body> res;
//        http::read(stream, buffer, res);
//
//        stream.socket().shutdown(tcp::socket::shutdown_both);
//
//        std::string body = beast::buffers_to_string(res.body().data());
//        return json::parse(body);
//    }
//    catch (const std::exception& e) {
//        std::cerr << "에러: " << e.what() << std::endl;
//        return {};
//    }
//}
//
//CNetwork_Manager* CNetwork_Manager::Create()
//{
//	CNetwork_Manager* pInstance = new CNetwork_Manager();
//
//	if (FAILED(pInstance->Initialize()))
//	{
//		MSG_BOX(TEXT("Failed to Created : CNetwork_Manager"));
//		Safe_Release(pInstance);
//	}
//
//	return pInstance;
//}
//
//void CNetwork_Manager::Free()
//{
//	__super::Free();
//
//}
