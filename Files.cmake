LIST (APPEND dms_SOURCES
    src/common.cc
    src/dms.cc
    src/group_value.cc
    src/message.cc
    src/schema.cc
	src/sequence_value.cc
	src/simple_value.cc
	src/value.cc
	src/wire_format.cc
)

LIST (APPEND dms_HEADERS
	include/dms.h
	src/byte_array.h
	src/common.h
	src/group_value.h
	src/memory_allocator.h
	src/message.h
	src/schema.h
	src/sequence_value.h
	src/simple_value.h
	src/value.h
	src/wire_format.h
	src/wire_format-inl.h
)