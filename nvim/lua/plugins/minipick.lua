local win_config = function()
    local height = math.floor(0.618 * vim.o.lines)
    local width = math.floor(0.618 * vim.o.columns)
    return {
        anchor = 'NW', height = height, width = width,
        row = math.floor(0.5 * (vim.o.lines - height)),
        col = math.floor(0.5 * (vim.o.columns - width)),
    }
end

return {
    "nvim-mini/mini.pick",
    version = "*",
    dependencies = { "nvim-mini/mini.icons" },
    config = function()
        require("mini.pick").setup({
            window = { config = win_config }
        })
    end
}
