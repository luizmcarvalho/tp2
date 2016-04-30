CC = gcc
# -g : allows use of GNU Debugger
# -Wall : show all warnings
CFLAGS = -g # -Wall
LIBS = # None yet...
CSOURCE = client.c tp_clnt.c tp_xdr.c
SSOURCE = server.c tp_svc.c tp_xdr.c logger.h logger.c
RPCSRC = tp.x
RPCGEN = tp.h tp_clnt.c tp_svc.c tp_xdr.c
CLIENT = client
SERVER = server

all: $(CLIENT) $(SERVER)

$(CLIENT): $(CSOURCE) $(RPCGEN)
	$(CC) $(LIBS) $(CFLAGS) -o $(CLIENT) $(CSOURCE)

$(SERVER): $(SSOURCE) $(RPCGEN)
	$(CC) $(LIBS) $(CFLAGS) -o $(SERVER) $(SSOURCE)

$(RPCGEN): $(RPCSRC)
	rpcgen $(RPCSRC)

# 'clean' rule for remove non-source files
# To use, call 'make clean'
# Note: you don't have to call this in between every
#       compilation, it's only in case you need to
#       clean out your directory for some reason.
clean:
	@# Using the '@' sign suppresses echoing
	@# the line while the command is run
	rm -f $(CLIENT) $(SERVER) $(RPCGEN)
