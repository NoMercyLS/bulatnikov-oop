#pragma once
#include "string"

const std::string HTTP_STRING = "http";
const std::string HTTPS_STRING = "https";

const unsigned short HTTP_DEFAULT_PORT = 80;
const unsigned short HTTPS_DEFAULT_PORT = 443;
const unsigned short MAX_PORT_VALUE = 65535;
const unsigned short MIN_PORT_VALUE = 1;

namespace ExceptionMessages
{
    const std::string EMPTY_URL = "Invalid URL. Usage: <protocol>://<domain>(:<port>)(/<document>)";
    const std::string INVALID_PROTOCOL = "Invalid protocol. Usage: :// after protocol.";
    const std::string INVALID_DOMAIN = "Invalid domain.";
    const std::string INVALID_PORT = "Invalid port. Usage: :<port>";
    const std::string PORT_OUT_OF_RANGE = "Invalid port. Port must be in range [1, 65535]";
    const std::string INVALID_DOCUMENT = "Invalid document.";
    const std::string INVALID_PROTOCOL_TYPE = "Invalid protocol. Usage: http or https";
}
