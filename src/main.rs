mod demo_lib;

fn main() {
    let events = demo_lib::get_events();
    println!("count={}, events={:?}", events.len(), events.as_ptr());
    for event in events {
        println!("Processing event of type {:?}", event);
    }
    println!("Done!");
}
