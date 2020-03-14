mod demo_lib;
use demo_lib::DlEvent;

fn main() {
    let events = demo_lib::get_events();
    println!("count={}, events={:?}", events.len(), events.as_ptr());
    for event in events {
        println!("Processing event of type {:?}", event);
        match event {
            DlEvent::CreatedEvent { creationString } => println!("Doing nothing with {:?}", creationString),
            DlEvent::DestroyedEvent { destroyedByte } => println!("Doing nothing with {:?}", destroyedByte),
            DlEvent::ChangedEvent  { changedState } => println!("Doing nothing with {:?}", changedState),
        }
    }
    println!("Done!");
}
