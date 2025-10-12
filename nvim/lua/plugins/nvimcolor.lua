return {
    {
        "catgoose/nvim-colorizer.lua",
        event = "BufReadPre",
        opts = {},
        config = function()
            require("colorizer").setup({})
        end
    },
    {
        "fladson/vim-kitty",
        ft = "kitty",
    }
}
