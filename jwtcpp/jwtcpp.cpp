#include <jwt-cpp/jwt.h>
#include <iostream>

int main() 
{
	auto token = jwt::create()
		.set_type("JWS")
		.set_issuer("auth0")
		.set_payload_claim("sample", jwt::claim(std::string("test")))
		.sign(jwt::algorithm::hs256{ "secret" });

	auto decoded = jwt::decode(token);

	for (auto& e : decoded.get_payload_json())
		std::cout << e.first << " = " << e.second << std::endl;
}