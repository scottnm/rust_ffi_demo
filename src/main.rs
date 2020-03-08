#[repr(C)]
enum FFI_DL_EventType
{
    Created,
    Destroyed,
    Changed,
}

#[repr(C)]
struct FFI_DL_Event
{
    event_type: FFI_DL_EventType,
}

// TODO: add rest of FFI definitions

type FFI_DL_EventList = *const *const FFI_DL_EventType;

#[link(name = "demo_lib_static", kind = "static")]
extern {
    fn demo_lib_get_events_ffi(/* Out */ count: *mut u32, /* Out */ events: *mut FFI_DL_EventList) -> i32;
}

fn main() {
    println!("Hello, world!");
}
