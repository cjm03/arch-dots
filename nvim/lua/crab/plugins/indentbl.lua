return {
    "lukas-reineke/indent-blankline.nvim",
    event = { "BufReadPre", "BufNewFile" },
    main = "ibl",
    config = function()
        local highlight = { "HighlightColor" }
        local hooks = require "ibl.hooks"
        hooks.register(hooks.type.HIGHLIGHT_SETUP, function()
            vim.api.nvim_set_hl(0, "HighlightColor", { fg = "#fffff0"})
        end)
        require("ibl").setup({
            -- indent = { highlight = highlight }
            -- scope = { char = "⎽", highlight = highlight },
            scope = { highlight = highlight },
            indent = { char = "│" },
        })
    end
}
