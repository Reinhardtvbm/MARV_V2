#[derive(Debug)]
pub struct Packet {
    raw_packet: u32,
    packet_type: PacketType,
    packet_data: u32, 
}

impl Packet {
    pub fn new(raw_packet: u32) -> Self {
        Self {
            raw_packet,
            packet_type: ((raw_packet >> 24) as u8).into(),
            packet_data: raw_packet >> 8,
        }
    }   
}

#[derive(Debug)]
#[repr(u8)]
pub enum PacketType {
    RaceEnd = 0,    
    Invalid = 255,
}

impl Into<PacketType> for u8 {
     fn into(self) -> PacketType {
        match self {
            0 => PacketType::RaceEnd,
            _ => PacketType::Invalid,
        }
     }
}
