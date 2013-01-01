// Copyright (c) 2013 Plenluno All rights reserved.

#include <libj/js_data_view.h>
#include <libj/detail/js_data_view.h>

namespace libj {

JsDataView::Ptr JsDataView::create(Size length) {
	return JsDataView::create(JsArrayBuffer::create(length));
}

JsDataView::Ptr JsDataView::create(
	JsArrayBuffer::Ptr buffer,
	Size offset,
	Size length) {
	if (!buffer) return null();

	Size bufLen = buffer->byteLength();
	if (offset == NO_SIZE) offset = 0;
	if (length == NO_SIZE) length = bufLen - offset;
	if (offset > bufLen) return null();
	if (length > bufLen) return null();
	if (offset + length > bufLen) return null();

    return Ptr(new detail::JsDataView<JsDataView>(buffer, offset, length));
}

}   // namespace libj
