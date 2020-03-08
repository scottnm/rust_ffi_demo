use std::os::raw::c_char;

#[derive(Debug)]
#[repr(C)]
enum FFI_DL_EventType {
    Created,
    Destroyed,
    Changed,
}

#[repr(C)]
struct FFI_DL_Event {
    event_type: FFI_DL_EventType,
}

#[repr(C)]
struct FFI_DL_CreatedEvent {
    baseEvent: FFI_DL_Event,
    creationString: *const c_char,
}

#[repr(C)]
struct FFI_DL_DestroyedEvent {
    baseEvent: FFI_DL_Event,
    destroyedByte: u8,
}

#[derive(Debug)]
#[repr(C)]
enum FFI_ChangedState {
    A,
    B,
}

struct FFI_DL_ChangedEvent {
    baseEvent: FFI_DL_Event,
    changedState: FFI_ChangedState,
}

type FFI_DL_EventList = *const *const FFI_DL_Event;

#[link(name = "demo_lib_static", kind = "static")]
extern "C" {
    // TODO: rename this test api to more clearly look like an external api
    fn GetEvents(
        /* Out */ count: *mut u32,
        /* Out */ events: *mut FFI_DL_EventList,
    ) -> i32;
}

fn main() {
    unsafe {
        let mut count: u32 = 0;
        let count_ptr: *mut u32 = &mut count;
        let mut events_buffer: FFI_DL_EventList = std::ptr::null();
        let events_ptr: *mut FFI_DL_EventList = &mut events_buffer;
        let res = GetEvents(count_ptr, events_ptr);
        println!("res={}, count={}, events={:?}", res, count, events_buffer);

        let events = std::slice::from_raw_parts(events_buffer, count as usize);
        for event in events {
            println!("Processing event of type {:?}", (**event).event_type);
        }
    }
    println!("Done!");
}
