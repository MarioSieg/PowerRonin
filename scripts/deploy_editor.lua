print("Deploying editor...")

local function copy(src, dst)
    os.execute(string.format('copy "%s" "%s"', src, dst))
end