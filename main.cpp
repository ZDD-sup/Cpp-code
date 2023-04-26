#include <iostream>
#include <oatpp/network/Server.hpp>
#include "oatpp/web/server/HttpConnectionHandler.hpp"
#include "oatpp/network/tcp/server/ConnectionProvider.hpp"

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
// функция в которой реализуем запуск сервера
void runServer() {
	// создаём маршрутизатор (получаем объект типа указатель)
	auto router = oatpp::web::server::HttpRouter::createShared();

	// добовляем маршрут и обрабатывающий его хэндлер
	router->route("GET", "/sum", std::make_shared<SumHandler>());

	// создаём ConnectionHandler и пеередаём ему маршрутизатор
	auto connectionHandler = oatpp::web::server::HttpConnectionHandler::createShared(router);
	// создаём провайдер
	// указываем хост и порт
	auto connectionProvider = oatpp::network::tcp::server::ConnectionProvider::createShared(
		{"localHost", 8000, oatpp::network::Address::IP_4}
	);
	// создаём сервер с помощью провайдера и хэндлера
	oatpp::network::Server server(connectionProvider, connectionHandler);

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