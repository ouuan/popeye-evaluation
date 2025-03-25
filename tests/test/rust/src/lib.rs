use std::ffi::c_void;

#[allow(unused)]
extern "C" {
    fn popeye_make_object(size: u64) -> *mut c_void;
    fn popeye_make_message() -> *mut u8;
    fn popeye_make_message_length() -> u32;
}

fn parse(message: &[u8]) {
    assert_eq!(message[0], message[1]);
    assert_eq!(message[0], message[2]);
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
