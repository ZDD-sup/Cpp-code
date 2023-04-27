#include <iostream>
#include <oatpp/network/Server.hpp>
#include "oatpp/web/server/HttpConnectionHandler.hpp"
#include "oatpp/network/tcp/server/ConnectionProvider.hpp"
#include "AppComponent.hpp"
#include "dto/ResultDto.hpp"
#include "dto/HelloDto.hpp"
#include "controller/MathController.hpp"


//class SumHandler : public oatpp::web::server::HttpRequestHandler {
//public:
//	std::shared_ptr<OutgoingResponse> handle(const std::shared_ptr<IncomingRequest>& request) override {
//		
//	}
//};
class HelloHandler : public oatpp::web::server::HttpRequestHandler {
public:
	std::shared_ptr<OutgoingResponse> handle(const std::shared_ptr<IncomingRequest>& request) override {
		// получаем ObjectMapper
		OATPP_COMPONENT(std::shared_ptr<oatpp::data::mapping::ObjectMapper>, objectMapper);
		// создаем пустой массив
		auto list = HelloDto::createShared();

		// наполняем массив
		auto element1 = ElementDto::createShared();
		list->elements = {};
		element1->id = 1;
		element1->name = "Mik";
		auto ele2 = ElementDto::createShared();
		ele2->id = 2;
		ele2->name = "Di";

		list->elements->push_back(element1);
		list->elements->push_back(ele2);
		OATPP_LOGD("App", "/hello выполнено");
		return ResponseFactory::createResponse(Status::CODE_200, list, objectMapper);
	}
};
// функция в которой реализуем запуск сервера
void runServer() {
	AppComponent components;
	
	// получаем роутер
	OATPP_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, httpRouter);
	// подключаем контроллер к роутеру
	httpRouter->addController(std::make_shared<MathController>());

	// получаем ConnectionHandler
	OATPP_COMPONENT(std::shared_ptr<oatpp::network::ConnectionHandler>, serverConnectionHandler);
	// получаем ServerConnectionProvider
	OATPP_COMPONENT(std::shared_ptr<oatpp::network::ServerConnectionProvider>, serverConnectionProvider);
	// создаём сервер
	oatpp::network::Server server(serverConnectionProvider, serverConnectionHandler);
	
	OATPP_LOGI("App", "Сервер запущен!");

	// стартуем сервер
	server.run();
}



int main() {
	setlocale(LC_ALL, "Rus");
	oatpp::base::Environment::init();
	// вызов функции для запуска
	runServer();

	/*std::cout << "\nEnvironment:\n";
	std::cout << "objectsCount = " << oatpp::base::Environment::getObjectsCount() << "\n";
	std::cout << "objectsCreated = " << oatpp::base::Environment::getObjectsCreated() << "\n\n";*/
	return 0;
} 