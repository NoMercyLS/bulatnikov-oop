#pragma once
#include "string"
using namespace std;

const string HTTP_STRING = "http";
const string HTTPS_STRING = "https";

const unsigned short HTTP_DEFAULT_PORT = 80;
const unsigned short HTTPS_DEFAULT_PORT = 443;
const unsigned short MAX_PORT_VALUE = 65535;
const unsigned short MIN_PORT_VALUE = 1;

namespace ExceptionMessages
{
    const string EMPTY_URL = "Invalid URL. Usage: <protocol>://<domain>(:<port>)(/<document>)";
    const string INVALID_PROTOCOL = "Invalid protocol. Usage: :// after protocol.";
    const string INVALID_DOMAIN = "Invalid domain.";
    const string INVALID_PORT = "Invalid port. Usage: :<port>";
    const string PORT_OUT_OF_RANGE = "Invalid port. Port must be in range [1, 65535]";
    const string INVALID_DOCUMENT = "Invalid document.";
    const string INVALID_PROTOCOL_TYPE = "Invalid protocol. Usage: http or https";
}
