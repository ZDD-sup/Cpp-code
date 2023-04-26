#include <iostream>
#include <oatpp/network/Server.hpp>
#include "oatpp/web/server/HttpConnectionHandler.hpp"
#include "oatpp/network/tcp/server/ConnectionProvider.hpp"
#include "AppComponent.hpp"


class SumHandler : public oatpp::web::server::HttpRequestHandler {
public:
	std::shared_ptr<OutgoingResponse> handle(const std::shared_ptr<IncomingRequest>& request) override {
		// можно получить параметры Query String
		auto aPtr = request->getQueryParameter("a").get();
		auto bPtr = request->getQueryParameter("b").get();

		// получаем значение заголовка в виде строки (std::string)
		auto acceptLanguaHandltr = request->getHeader("Accept-Language").get();
		// записываем его в консоль как Warning
		OATPP_LOGW("App", acceptLanguaHandltr->c_str());


		if (aPtr == nullptr || bPtr == nullptr) {
			OATPP_LOGE("App", "Не все параметры указаны!");
			return ResponseFactory::createResponse(Status::CODE_400, "Не все параметры указаны!");
		}
		// преобразование строки в float
		float a = atof(aPtr->c_str());
		float b = atof(bPtr->c_str());

		// создадим ответ, но не возращаем его пока
		auto response = ResponseFactory::createResponse(Status::CODE_200, std::to_string(a + b));
		// добавим в заголовок
		response->putHeaderIfNotExists("SumResult", std::to_string(a + b));
		
		OATPP_LOGD("App", "Результат вычислен успешно!");

		// а теперь возращаем ответ уже с заголовком
		return response;
	}
};
class HelloHandler : public oatpp::web::server::HttpRequestHandler {
public:
	std::shared_ptr<OutgoingResponse> handle(const std::shared_ptr<IncomingRequest>& request) override {
		OATPP_COMPONENT(std::string, helloString);
		return ResponseFactory::createResponse(Status::CODE_200, helloString);
	}
};
// функция в которой реализуем запуск сервера
void runServer() {
	AppComponent components;
	
	// получаем роутер
	OATPP_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, httpRouter);
	httpRouter->route("GET", "/sum", std::make_shared<SumHandler>());
	httpRouter->route("GET", "/hello", std::make_shared<HelloHandler>());

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