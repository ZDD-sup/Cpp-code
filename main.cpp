#include <iostream>
#include <oatpp/network/Server.hpp>
#include "oatpp/web/server/HttpConnectionHandler.hpp"
#include "oatpp/network/tcp/server/ConnectionProvider.hpp"

class SumHandler : public oatpp::web::server::HttpRequestHandler {
public:
	std::shared_ptr<OutgoingResponse> handle(const std::shared_ptr<IncomingRequest>& request) override {
		// ����� �������� ��������� Query String
		auto aPtr = request->getQueryParameter("a").get();
		auto bPtr = request->getQueryParameter("b").get();

		// �������� �������� ��������� � ���� ������ (std::string)
		auto acceptLanguaHandltr = request->getHeader("Accept-Language").get();
		// ���������� ��� � ������� ��� Warning
		OATPP_LOGW("App", acceptLanguaHandltr->c_str());


		if (aPtr == nullptr || bPtr == nullptr) {
			OATPP_LOGE("App", "�� ��� ��������� �������!");
			return ResponseFactory::createResponse(Status::CODE_400, "�� ��� ��������� �������!");
		}
		// �������������� ������ � float
		float a = atof(aPtr->c_str());
		float b = atof(bPtr->c_str());

		// �������� �����, �� �� ��������� ��� ����
		auto response = ResponseFactory::createResponse(Status::CODE_200, std::to_string(a + b));
		// ������� � ���������
		response->putHeaderIfNotExists("SumResult", std::to_string(a + b));
		
		OATPP_LOGD("App", "��������� �������� �������!");

		// � ������ ��������� ����� ��� � ����������
		return response;
	}
};
// ������� � ������� ��������� ������ �������
void runServer() {
	// ������ ������������� (�������� ������ ���� ���������)
	auto router = oatpp::web::server::HttpRouter::createShared();

	// ��������� ������� � �������������� ��� �������
	router->route("GET", "/sum", std::make_shared<SumHandler>());

	// ������ ConnectionHandler � �������� ��� �������������
	auto connectionHandler = oatpp::web::server::HttpConnectionHandler::createShared(router);
	// ������ ���������
	// ��������� ���� � ����
	auto connectionProvider = oatpp::network::tcp::server::ConnectionProvider::createShared(
		{"localHost", 8000, oatpp::network::Address::IP_4}
	);
	// ������ ������ � ������� ���������� � ��������
	oatpp::network::Server server(connectionProvider, connectionHandler);

	OATPP_LOGI("App", "������ �������!");

	// �������� ������
	server.run();
}



int main() {
	setlocale(LC_ALL, "Rus");
	oatpp::base::Environment::init();
	// ����� ������� ��� �������
	runServer();

	/*std::cout << "\nEnvironment:\n";
	std::cout << "objectsCount = " << oatpp::base::Environment::getObjectsCount() << "\n";
	std::cout << "objectsCreated = " << oatpp::base::Environment::getObjectsCreated() << "\n\n";*/
	return 0;
} 