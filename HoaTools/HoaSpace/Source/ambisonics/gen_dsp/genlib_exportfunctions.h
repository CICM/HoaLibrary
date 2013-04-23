#ifndef GENLIB_EXPORT_FUNCTIONS_H
#define GENLIB_EXPORT_FUNCTIONS_H 1

typedef char *t_ptr; 

t_ptr sysmem_newptr(t_ptr_size size);
t_ptr sysmem_newptrclear(t_ptr_size size);
t_ptr sysmem_resizeptr(void *ptr, t_ptr_size newsize);
t_ptr sysmem_resizeptrclear(void *ptr, t_ptr_size newsize);
t_ptr_size sysmem_ptrsize(void *ptr);
void sysmem_freeptr(void *ptr);
void sysmem_copyptr(const void *src, void *dst, t_ptr_size bytes);
unsigned long systime_ticks(void);

void genlib_report_error(const char *s);
void genlib_report_message(const char *s);
void set_zero64(double *mem, long size);

#endif // GENLIB_EXPORT_FUNCTIONS_H
