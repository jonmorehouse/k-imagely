#ifndef KIMAGELY_SERVER_INCLUDED
#define KIMAGELY_SERVER_INCLUDED

extern const int URI_MAXIMUM_LENGTH;
extern const int QUERY_ARG_MAXIMUM_LENGTH;
extern const char* HTTP_PROTOCOL;

typedef enum {
  UNABLE_TO_LISTEN,
  UNABLE_TO_ACCEPT,
  HTTP_INVALID_PROTOCOL,
  HTTP_INVALID_ROUTE,
  HTTP_URL_TOO_LONG,
} SERVER_ERRORS;

// create an enum + array of const char
#define FOREACH_HTTP_METHOD(HTTP_METHOD) \
  HTTP_METHOD(GET) \
  HTTP_METHOD(POST) \
  HTTP_METHOD(PUT) \
  HTTP_METHOD(DELETE) \
  HTTP_METHOD(OPTIONS) \

#define GENERATE_ENUM(ENUM) ENUM, 
#define GENERATE_STRING(STRING) #STRING,

enum HTTP_METHOD_ENUM {
  FOREACH_HTTP_METHOD(GENERATE_ENUM)
};

static const char *HTTP_METHOD_STRING[] = {
  FOREACH_HTTP_METHOD(GENERATE_STRING)
};

typedef struct {
  int method;
  _Bool isHTTP;
  int queryArgsCount;
  char ** queryArgs;
  int error;
  
  // handlerMethod
  // query_arguments
} Request;

typedef struct {
  // logChannel
  // routeTable
} Server;

void startServer(Server *);

#endif
