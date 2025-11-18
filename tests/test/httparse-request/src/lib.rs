use httparse::{EMPTY_HEADER, Request};
use std::ffi::c_void;

#[allow(unused)]
extern "C" {
    fn popeye_make_object(size: u64) -> *mut c_void;
    fn popeye_make_message() -> *mut u8;
    fn popeye_make_message_length() -> u32;
}

fn parse(message: &[u8]) {
    let mut headers = [EMPTY_HEADER; 4];
    let mut req = Request::new(&mut headers);
    req.parse(message).unwrap();
}

#[no_mangle]
pub fn popeye_main() -> i32 {
    let message = unsafe {
        let message = popeye_make_message();
        let length = popeye_make_message_length();
        std::slice::from_raw_parts(message, length as usize)
    };
    parse(message);
    0
}
