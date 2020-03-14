use std::os::raw::c_char;

// TODO: don't just make every field public

#[derive(Debug)]
#[repr(C)]
enum FFI_DL_EventType {
    Created,
    Destroyed,
    Changed,
}

#[repr(C)]
struct FFI_DL_Event {
    pub event_type: FFI_DL_EventType,
}

#[repr(C)]
struct FFI_DL_CreatedEvent {
    pub baseEvent: FFI_DL_Event,
    pub creationString: *const c_char,
}

#[repr(C)]
struct FFI_DL_DestroyedEvent {
    pub baseEvent: FFI_DL_Event,
    pub destroyedByte: u8,
}

#[derive(Debug, Clone, Copy)]
#[repr(C)]
pub enum FFI_ChangedState {
    A,
    B,
}

struct FFI_DL_ChangedEvent {
    pub baseEvent: FFI_DL_Event,
    pub changedState: FFI_ChangedState,
}

type FFI_DL_EventList = *const *const FFI_DL_Event;

#[link(name = "demo_lib_static", kind = "static")]
extern "C" {
    fn DL_GetEvents(
        /* Out */ count: *mut u32,
        /* Out */ events: *mut FFI_DL_EventList,
    ) -> i32;
}

// The FFI_ChangedState enum is fine to present in our safe interface, but let's alias away that
// gnarly FFI name
pub type ChangedState = FFI_ChangedState;

// FIXME: is there anyway to just present a rust-safe view of things without copying? I feel like
// this is a job for slices but idk
#[derive(Debug)]
pub enum DlEvent {
    // FIXME: avoid a string allocation+copy
    CreatedEvent { creationString: String },
    DestroyedEvent { destroyedByte: u8 },
    ChangedEvent  { changedState: ChangedState },
}

// FIXME: maybe there should be some wrapping structure that on drop(..) calls ReturnEvents or
// something. Then the lifetime of the events could be tied to the lifetime of the structure which
// would be more semantically correct.
pub fn get_events() -> Vec<DlEvent> {
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
        for event_ptr in std::slice::from_raw_parts(events_buffer, count as usize) {
            // Our lib should never return a nullptr so the unwrap matches the API guarantee
            let event = event_ptr.as_ref().unwrap();
            let safe_event = match event.event_type {
                /*
                FFI_DL_EventType::Created => {
                    DlEvent::Created { creationString: }
                },
                */
                FFI_DL_EventType::Destroyed => {
                    let destroyedByte = std::mem::transmute::<&FFI_DL_Event, &FFI_DL_DestroyedEvent>(event).destroyedByte;
                    DlEvent::DestroyedEvent { destroyedByte }
                },
                FFI_DL_EventType::Changed => {
                    let changedState = std::mem::transmute::<&FFI_DL_Event, &FFI_DL_ChangedEvent>(event).changedState;
                    DlEvent::ChangedEvent { changedState }
                },
                // FIXME: stub
                _ => DlEvent::DestroyedEvent { destroyedByte: 0 }
            };

            safe_events.push(safe_event)
        }
        safe_events
    }
}
