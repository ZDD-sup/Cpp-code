#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"

#include OATPP_CODEGEN_BEGIN(ApiController)

class MathController :public oatpp::web::server::api::ApiController {
private:
	ResultDto::Wrapper createDto(Float32 a, Float32 b, Float32 result) {
		// ��������� ���� ������ (DTO)
		ResultDto::Wrapper dto = ResultDto::createShared();
		dto->value = result;
		dto->message = "Success!";
		dto->arguments = ArgumentsDto::createShared();
		dto->arguments->a = a;
		dto->arguments->b = b;
		return dto;
	};
public:
	MathController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper))
		: oatpp::web::server::api::ApiController(objectMapper)
	{ }

	ENDPOINT("GET", "/math/sum", sum, QUERY(Float32, a, "a"), QUERY(Float32, b, "b")) {
		//�������� ObjectMapper
		OATPP_COMPONENT(std::shared_ptr<oatpp::data::mapping::ObjectMapper>, objectMapper);

		// ����������!
		/*if (a == NULL || b == NULL ) {
			OATPP_LOGE("App", "�� ��� ��������� �������!");
			return ResponseFactory::createResponse(Status::CODE_400, "�� ��� ��������� �������!");
		}*/

		OATPP_LOGD("App", "��������� �������� �������");

		// � ������ ��������� ����� ��� � ����������
		return ResponseFactory::createResponse(Status::CODE_200, createDto(a, b, a + b), objectMapper);;
	};
};

#include OATPP_CODEGEN_END(ApiController)