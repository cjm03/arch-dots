return {
    "folke/trouble.nvim",
    opts = {},
    cmd = "Trouble",
    lazy = true,
    keys = {
        {
            "<leader>xx",
            "<cmd>Trouble diagnostics toggle<cr>",
            desc = "Workspace Diagnostics(Trouble)",
        },
        {
            "<leader>xX",
            "<cmd>Trouble diagnostics toggle filter.buf=0<cr>",
            desc = "Buffer Diagnostics(Trouble)",
        },
    },
}
