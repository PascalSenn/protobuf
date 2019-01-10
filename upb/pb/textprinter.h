/*
** upb::pb::TextPrinter (upb_textprinter)
**
** Handlers for writing to protobuf text format.
*/

#ifndef UPB_TEXT_H_
#define UPB_TEXT_H_

#include "upb/sink.h"

#ifdef __cplusplus
namespace upb {
namespace pb {
class TextPrinter;
}  /* namespace pb */
}  /* namespace upb */
#endif

UPB_DECLARE_TYPE(upb::pb::TextPrinter, upb_textprinter)

#ifdef __cplusplus

class upb::pb::TextPrinter {
 public:
  /* The given handlers must have come from NewHandlers().  It must outlive the
   * TextPrinter. */
  static TextPrinter *Create(Environment *env, const upb::Handlers *handlers,
                             BytesSink *output);

  void SetSingleLineMode(bool single_line);

  Sink* input();

  /* If handler caching becomes a requirement we can add a code cache as in
   * decoder.h */
  static HandlerCache* NewCache();
};

#endif

UPB_BEGIN_EXTERN_C

/* C API. */
upb_textprinter *upb_textprinter_create(upb_env *env, const upb_handlers *h,
                                        upb_bytessink *output);
void upb_textprinter_setsingleline(upb_textprinter *p, bool single_line);
upb_sink *upb_textprinter_input(upb_textprinter *p);

upb_handlercache *upb_textprinter_newcache();

UPB_END_EXTERN_C

#ifdef __cplusplus

namespace upb {
namespace pb {
inline TextPrinter *TextPrinter::Create(Environment *env,
                                        const upb::Handlers *handlers,
                                        BytesSink *output) {
  return upb_textprinter_create(env, handlers, output);
}
inline void TextPrinter::SetSingleLineMode(bool single_line) {
  upb_textprinter_setsingleline(this, single_line);
}
inline Sink* TextPrinter::input() {
  return upb_textprinter_input(this);
}
inline HandlerCache* TextPrinter::NewCache() {
  return upb_textprinter_newcache();
}
}  /* namespace pb */
}  /* namespace upb */

#endif

#endif  /* UPB_TEXT_H_ */
