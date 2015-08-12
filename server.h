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
  HTTP_INVALID_HTTP_METHOD,
} SERVER_ERRORS;

// create an enum + array of const char
typedef enum {
  HTTP_GET,
  HTTP_POST,
  HTTP_PUT,
  HTTP_DELETE,
  HTTP_OPTIONS,
} HTTP_METHODS;

typedef struct QueryArg QueryArg;
struct QueryArg {
  char * key;
  char * value;
  QueryArg *next;
};

typedef struct {
  int HTTPMethod;
  _Bool isHTTP;
  int queryArgsCount;
  QueryArg * queryArg;
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
