#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/Types.hpp"
#include OATPP_CODEGEN_BEGIN(DTO)
//#include OATTP_CODEGEN_END(DTO)

class ArgumentsDto : public oatpp::DTO {
	DTO_INIT(ArgumentsDto, DTO);
	DTO_FIELD(Float32, a);
	DTO_FIELD(Float32, b);
};
//������ ������, ������� ����� ��������� ����� ���������� �����
class ResultDto : public oatpp::DTO {
	DTO_INIT(ResultDto, DTO);
	DTO_FIELD(Float32, value);
	DTO_FIELD(String, message);
	DTO_FIELD(Object<ArgumentsDto>, arguments);
};


