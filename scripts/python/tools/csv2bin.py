import array

with open('input.csv', 'rt') as f:
    text = f.read()
    entries = text.split(',')
    values = [int(x, 16) for x in entries]
    # do a scalar here: if your input goes from [-100, 100] then
    #   you may need to translate/scale into [0, 2^16-1] for
    #   16-bit PCM
    # e.g.:
    #   values = [(val * scale) for val in values]

with open('output.bin', 'wb') as out:
    pcm_vals = array.array('B', values) # 8-bit unsigned
    pcm_vals.tofile(out)