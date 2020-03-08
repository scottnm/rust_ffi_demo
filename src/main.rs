use std::os::raw::c_char;

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

#[repr(C)]
struct FFI_DL_CreatedEvent
{
    baseEvent: FFI_DL_Event,
    creationString: *const c_char,
}

#[repr(C)]
struct FFI_DL_DestroyedEvent
{
    baseEvent: FFI_DL_Event,
    destroyedByte: u8,
}

#[repr(C)]
enum FFI_ChangedState
{
    A,
    B,
}

struct FFI_DL_ChangedEvent
{
    baseEvent: FFI_DL_Event,
    changedState: FFI_ChangedState,
}

type FFI_DL_EventList = *const *const FFI_DL_EventType;

#[link(name = "demo_lib_static", kind = "static")]
extern {
    // TODO: rename this test api to be better
    fn GetEvents(/* Out */ count: *mut u32, /* Out */ events: *mut FFI_DL_EventList) -> i32;
}

fn main() {
    unsafe {
        let mut count: u32 = 0;
        let count_ptr: *mut u32 = &mut count;
        let mut events: FFI_DL_EventList = std::ptr::null();
        let events_ptr: *mut FFI_DL_EventList = &mut events;
        let res = GetEvents(count_ptr, events_ptr);
        println!("res={}, count={}, events={:?}", res, count, events);
    }
    println!("Done!");
}
