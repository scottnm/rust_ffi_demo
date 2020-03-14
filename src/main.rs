mod demo_lib;
use demo_lib::*;

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
