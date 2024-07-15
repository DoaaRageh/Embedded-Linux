#include<iostream>

enum class ErrorCode 
{
    BadRequest=400,
    NotFound=404,
    ServerError=500,
    GatewayTimeout=504
};

void printError(ErrorCode error)
{
    if(ErrorCode::BadRequest == error)
    {
        std::cout << "Bad Request" << std::endl;
    }
    else if(ErrorCode::NotFound == error)
    {
        std::cout << "Not Found" << std::endl;
    }
    else if(ErrorCode::ServerError == error)
    {
        std::cout << "Server Error" << std::endl;
    }
    else if(ErrorCode::GatewayTimeout == error)
    {
        std::cout << "Gateway Timeout" << std::endl;
    }
}
int main()
{
    ErrorCode bad_requet = ErrorCode::BadRequest;
    ErrorCode not_found = ErrorCode::NotFound;
    ErrorCode server_error = ErrorCode::ServerError;
    ErrorCode gateway_timeout = ErrorCode::GatewayTimeout;

    printError(bad_requet);
    printError(not_found);
    printError(server_error);
    printError(gateway_timeout);
}


