use std::os::raw::c_char;

// TODO: instead of publicizing all of these c structures, is there
// any way to get a "rust"ier safe view of the structs

// TODO: don't just make every field public

#[derive(Debug)]
#[repr(C)]
pub enum FFI_DL_EventType {
    Created,
    Destroyed,
    Changed,
}

#[repr(C)]
pub struct FFI_DL_Event {
    pub event_type: FFI_DL_EventType,
}

#[repr(C)]
pub struct FFI_DL_CreatedEvent {
    pub baseEvent: FFI_DL_Event,
    pub creationString: *const c_char,
}

#[repr(C)]
pub struct FFI_DL_DestroyedEvent {
    pub baseEvent: FFI_DL_Event,
    pub destroyedByte: u8,
}

#[derive(Debug)]
#[repr(C)]
pub enum FFI_ChangedState {
    A,
    B,
}

pub struct FFI_DL_ChangedEvent {
    pub baseEvent: FFI_DL_Event,
    pub changedState: FFI_ChangedState,
}

pub type FFI_DL_EventList = *const *const FFI_DL_Event;

#[link(name = "demo_lib_static", kind = "static")]
extern "C" {
    fn DL_GetEvents(
        /* Out */ count: *mut u32,
        /* Out */ events: *mut FFI_DL_EventList,
    ) -> i32;
}

// FIXME: maybe there should be some wrapping structure that on drop(..) calls ReturnEvents or
// something. Then the lifetime of the events could be tied to the lifetime of the structure which
// would be more semantically correct.
pub fn get_events() -> Vec<&'static FFI_DL_Event> {
    unsafe {
        let mut count: u32 = 0;
        let count_ptr: *mut u32 = &mut count;
        let mut events_buffer: FFI_DL_EventList = std::ptr::null();
        let events_ptr: *mut FFI_DL_EventList = &mut events_buffer;
        let res = DL_GetEvents(count_ptr, events_ptr);
        if res != 0 {
            panic!("DL_GetEvents failed! res={}", res);
        }

        // FIXME: blech an allocation on every get_events call? what can I do to get rid of this?
        let mut safe_events = Vec::new();
        for event in std::slice::from_raw_parts(events_buffer, count as usize) {
            // Our lib should never return a nullptr so the unwrap matches the API guarantee
            safe_events.push(event.as_ref().unwrap())
        }
        safe_events
    }
}
