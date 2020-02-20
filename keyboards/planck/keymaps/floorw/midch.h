
void chordon(uint16_t keycode, bool maj)
{
    uint8_t note = midi_compute_note(keycode);
    uint8_t velocity = (midi_config.velocity + 1) * (128 / (MIDI_VELOCITY_MAX - MIDI_VELOCITY_MIN + 1));
    midi_send_noteon(&midi_device, 0, note, velocity - 14);
    midi_send_noteon(&midi_device, 0, note + 3 + maj, velocity - 14);
    midi_send_noteon(&midi_device, 0, note - 5, velocity - 14);
}

void chordoff(uint16_t keycode, bool maj)
{
    uint8_t note = midi_compute_note(keycode);
    uint8_t velocity = (midi_config.velocity + 1) * (128 / (MIDI_VELOCITY_MAX - MIDI_VELOCITY_MIN + 1));
    midi_send_noteoff(&midi_device, 0, note, velocity - 14);
    midi_send_noteoff(&midi_device, 0, note + 3 + maj, velocity - 14);
    midi_send_noteoff(&midi_device, 0, note - 5, velocity - 14);
}

void basson(uint16_t keycode)
{
    uint8_t note = midi_compute_note(keycode);
    uint8_t velocity = (midi_config.velocity + 1) * (128 / (MIDI_VELOCITY_MAX - MIDI_VELOCITY_MIN + 1));
    midi_send_noteon(&midi_device, 0, note, velocity - 14);
    midi_send_noteon(&midi_device, 0, note + 12, velocity - 14);
}

void bassoff(uint16_t keycode)
{
    uint8_t note = midi_compute_note(keycode);
    uint8_t velocity = (midi_config.velocity + 1) * (128 / (MIDI_VELOCITY_MAX - MIDI_VELOCITY_MIN + 1));
    midi_send_noteoff(&midi_device, 0, note, velocity - 14);
    midi_send_noteoff(&midi_device, 0, note + 12, velocity - 14);
}
