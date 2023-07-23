use std::{net::{TcpListener, TcpStream}, io::{BufReader, Read}};

use crate::packet::Packet;

mod packet;

const SERVER_ADDR: &str = "127.0.0.1:3000";

fn main() {
    // setup the server to listen for connections on port 3000
    let tcp_listener = TcpListener::bind(SERVER_ADDR).unwrap();
    
    // listen for connections and handle them
    for stream in tcp_listener.incoming() {
        let stream = stream.unwrap();

        handle_connection(stream); 
    }
}

fn handle_connection(mut stream: TcpStream) {
    // read one byte from the connection which indicates the type of client that is connecting
    let mut buf = [255];

    stream.read_exact(&mut buf).unwrap();

    match buf[0] {
        // client is the MARV robot
        0 => handle_marvconnection(stream),
        
        // client is the webapp that controls the robot's state
        1 => handle_controllerapp(stream),
        
        // undefined client type
        _ => (),
    }
}

fn handle_controllerapp(mut stream: TcpStream) {
    println!("client connected as controller app");

    let f = BufReader::new(&mut stream);
    let mut raw_packet: u32 = 0;
    let mut byte_count = 0;

    for byte in f.bytes() {
        raw_packet |= (byte.unwrap() as u32) << ((3 - byte_count) * 8);
        byte_count += 1;

        if byte_count == 4 {
            println!("{:#034b} -> {:?}", raw_packet, Packet::new(raw_packet));
            byte_count = 0;
        }
    }
}

fn handle_marvconnection(mut stream: TcpStream) {
    println!("client connected as MARV");
    let f = BufReader::new(&mut stream);

    for byte in f.bytes() {
        println!("{}", byte.unwrap());
    }
}

struct PacketBytes([u8; 4]);

impl Into<u32> for PacketBytes {
    fn into(self) -> u32 {
        ((self.0[0] as u32) << 24) | ((self.0[1] as u32) << 16) | ((self.0[2] as u32) << 8) | (self.0[3] as u32)
    }
}
