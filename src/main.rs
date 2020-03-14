mod demo_lib;

fn main() {
    let events = demo_lib::get_events();
    println!("count={}, events={:?}", events.len(), events.as_ptr());
    for event in events {
        // FIXME: eliminate this unsafe block wrapping
        unsafe {
            println!("Processing event of type {:?}", (**event).event_type);
        }
    }
    println!("Done!");
}
