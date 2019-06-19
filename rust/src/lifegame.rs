use rand::Rng;
use std::{thread, time};

pub fn run() {
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

type Field = Vec<Vec<bool>>;

struct LifeGame {
    width: usize,
    height: usize,
    field: Field,
}

impl LifeGame {
    pub fn new(width: usize, height: usize) -> Self {
        LifeGame {
            width: width,
            height: height,
            field: vec![vec![false; width]; height],
        }
    }

    pub fn init_field(&mut self) {
        for y in 0..self.height {
            for x in 0..self.width {
                let alive = match rand::thread_rng().gen_range(0, 2) {
                    0 => false,
                    _ => true,
                };
                self.field[y][x] = alive;
            }
        }
    }

    pub fn next_field(&self) -> Self {
        let mut next = LifeGame::new(self.width, self.height);
        for y in 0..self.height {
            for x in 0..self.width {
                let neighbours = self.alive_neighbors_count(y, x);
                next.field[y][x] = self.should_be_alive(y, x, neighbours);
            }
        }
        next
    }

    pub fn dump(&self) {
        let mut buf = String::new();
        for line in self.field.iter() {
            let s = line
                .iter()
                .map(|row| if *row { 'o' } else { '.' })
                .collect::<String>();
            buf = format!("{}{}\n", buf, s);
        }
        print!("{}", buf);
    }

    fn pos_check(&self, x: i64, y: i64) -> bool {
        0 <= x && x < self.width as i64 && 0 <= y && y < self.height as i64
    }

    fn alive_neighbors_count(&self, y: usize, x: usize) -> usize {
        static D8: [(i64, i64); 8] = [
            (-1, -1),
            (-1, 0),
            (-1, 1),
            (0, -1),
            (0, 1),
            (1, -1),
            (1, 0),
            (1, 1),
        ];

        let mut res = 0;
        for &(dy, dx) in D8.iter() {
            let ny = dy + y as i64;
            let nx = dx + x as i64;
            if !self.pos_check(nx, ny) {
                continue;
            }
            if self.field[ny as usize][nx as usize] {
                res += 1;
            }
        }
        res
    }

    fn should_be_alive(&self, y: usize, x: usize, neighbours: usize) -> bool {
        match (self.field[y][x], neighbours) {
            (true, 2) => true,
            (_, 3) => true,
            (_, _) => false,
        }
    }
}
