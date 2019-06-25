use lifegame::lifegame::*;
use std::{thread, time};

fn main() {
    run();
}

fn run() {
    let width = 100;
    let height = 40;
    let mut lifegame = LifeGame::new(width, height);
    lifegame.init_field();

    loop {
        console_clear();
        lifegame.dump();
        lifegame = lifegame.next_field();
        thread::sleep(time::Duration::from_millis(100));
    }
}

fn console_clear() {
    print!("{0}[;H{0}[2J", 27 as char);
}
