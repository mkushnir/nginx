#include <ngx_config.h>
#include <ngx_core.h>
#include <nginx.h>

#include <dlfcn.h>

void
foo_run(int argc, char *const *argv)
{
    void *dl;
    unsigned i;

    if ((dl = dlopen(NULL, 0)) == NULL) {
        fprintf(stderr, "dlopen failed\n");
    } else {
        for (i = 0; ngx_module_names[i] != NULL; ++i) {
            char buf[128];
            void (*fn)(int, char *const *);

            (void)snprintf(buf, sizeof(buf), "%s_test", ngx_module_names[i]);
            fn = (void(*)(int, char *const *))dlsym(dl, buf);
            if (fn != NULL) {
                fn(argc, argv);
            } else {
                //fprintf(stderr, "no test for %s\n", ngx_module_names[i]);
            }
        }
        (void)dlclose(dl);
    }
}
