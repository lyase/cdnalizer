/* 
**  mod_cdnalizer.c -- Apache sample cdnalizer module
**  [Autogenerated via ``apxs -n cdnalizer -g'']
**
**  To play with this sample module first compile it into a
**  DSO file and install it into Apache's modules directory 
**  by running:
**
**    $ apxs -c -i mod_cdnalizer.c
**
**  Then activate it in Apache's apache2.conf file for instance
**  for the URL /cdnalizer in as follows:
**
**    #   apache2.conf
**    LoadModule cdnalizer_module modules/mod_cdnalizer.so
**    <Location /cdnalizer>
**    SetHandler cdnalizer
**    </Location>
**
**  Then after restarting Apache via
**
**    $ apachectl restart
**
**  you immediately can request the URL /cdnalizer and watch for the
**  output of this module. This can be achieved for instance via:
**
**    $ lynx -mime_header http://localhost/cdnalizer 
**
**  The output should be similar to the following one:
**
**    HTTP/1.1 200 OK
**    Date: Tue, 31 Mar 1998 14:42:22 GMT
**    Server: Apache/1.3.4 (Unix)
**    Connection: close
**    Content-Type: text/html
**  
**    The sample page from mod_cdnalizer.c
*/ 

#include "../Rewriter.hpp"
#include "../Config.hpp"
#include "filter.hpp"

extern "C" {
#include "httpd.h"
#include "http_config.h"
#include "http_protocol.h"
#include "ap_config.h"

static const char cdnalizer_filter_name[] = "CDNALIZER";

/*
static const command_rec cdnalizer_filter_cmds[] = {
    AP_INIT_RAW_ARGS("CDNRewriteRule", cmd_cdnrewriterule, NULL, OR_FILEINFO,
                     "an URL-applied regexp-pattern and a substitution (cdn) URL");
}
*/

static apr_status_t cdnalize_out_filter(ap_filter_t *filter, apr_bucket_brigade *bb)
{
    try {
        return cdnalizer::apache::filter(filter, bb);
    } catch (cdnalizer::apache::ApacheException& e) {
        return e.code;
    } catch (...) {
        // C doesn't have exceptions, so just let it know something weird went wrong
        return APR_OS_START_USERERR;
    }
}

static void cdnalizer_register_hooks(apr_pool_t *p)
{
    ap_register_output_filter(cdnalizer_filter_name, cdnalize_out_filter, NULL,
                              AP_FTYPE_CONTENT_SET);
}

/* Dispatch list for API hooks */
module AP_MODULE_DECLARE_DATA cdnalizer_module = {
    STANDARD20_MODULE_STUFF, 
    NULL,                  /* create per-dir    config structures */
    NULL,                  /* merge  per-dir    config structures */
    NULL,                  /* create per-server config structures */
    NULL,                  /* merge  per-server config structures */
    //cdnalizer_filter_cmds, /* table of config file commands       */
    NULL,
    cdnalizer_register_hooks  /* register hooks                      */
};

}
