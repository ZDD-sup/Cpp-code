#include <iostream>
#include <oatpp/network/Server.hpp>
#include "oatpp/web/server/HttpConnectionHandler.hpp"
#include "oatpp/network/tcp/server/ConnectionProvider.hpp"

class HelloHandler : public oatpp::web::server::HttpRequestHandler {
public:
	std::shared_ptr<OutgoingResponse> handle(const std::shared_ptr<IncomingRequest>& request) override {
		// создаём ответ, указываем код и сообщение
		// код 200 означает, что все хорошо
		return ResponseFactory::createResponse(Status::CODE_200, "Hello, world!");
	}
};
// функция в которой реализуем запуск сервера
void runServer() {
	// создаём маршрутизатор (получаем объект типа указатель)
	auto router = oatpp::web::server::HttpRouter::createShared();

	// добовляем маршрут и обрабатывающий его хэндлер
	router->route("GET", "/hello", std::make_shared<HelloHandler>());

	// создаём ConnectionHandler и пеередаём ему маршрутизатор
	auto connectionHandler = oatpp::web::server::HttpConnectionHandler::createShared(router);
	// создаём провайдер
	// указываем хост и порт
	auto connectionProvider = oatpp::network::tcp::server::ConnectionProvider::createShared(
		{"localHost", 8000, oatpp::network::Address::IP_4}
	);
	// создаём сервер с помощью провайдера и хэндлера
	oatpp::network::Server server(connectionProvider, connectionHandler);
	// стартуем сервер
	server.run();
}



int main() {
	oatpp::base::Environment::init();
	// вызов функции для запуска
	runServer();

	/*std::cout << "\nEnvironment:\n";
	std::cout << "objectsCount = " << oatpp::base::Environment::getObjectsCount() << "\n";
	std::cout << "objectsCreated = " << oatpp::base::Environment::getObjectsCreated() << "\n\n";*/
	return 0;
}