#ifndef SIGNAL_HANDLER_H
#define SIGNAL_HANDLER_H

typedef void (*signal_handler_on_signal)();

typedef struct {

} signal_handler;

signal_handler *signal_handler_create();
void signal_handler_destroy(signal_handler *self);
void signal_handler_add_on_signal(signal_handler *self,
                                  const signal_handler_on_signal on_signal);

#endif // SIGNAL_HANDLER_H
