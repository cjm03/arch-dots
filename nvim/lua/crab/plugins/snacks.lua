return {
    {
        "folke/snacks.nvim",
        priority = 1000,
        lazy = false,
        opts = {
            indent = {
                priority = 1,
                enabled = true,
                char = "│",
                only_scope = false,
                only_current = false,
                hl = "SnacksIndent",
            },
            animate = { enabled = false },
            explorer = {
                enabled = false,
                layout = {
                    cycle = false,
                }
            },
            quickfile = {
                enabled = true,
                exclude = {"latex"},
            },
            picker = {
                enabled = true,
                matchers = {
                    frecency = true,
                    cwd_bonus = true,
                },
                formatters = {
                    file = {
                        filename_first = false,
                        filename_only = false,
                        icon_width = 2,
                    },
                },
                layout = {
                    preset = "telescope",
                    cycle = false,
                },
                layouts = {
                    select = {
                        preview = false,
                        layout = {
                            backdrop = false,
                            width = 0.6,
                            min_width = 80,
                            height = 0.4,
                            min_height = 10,
                            box = "vertical",
                            border = "rounded",
                            title = "{title}",
                            title_pos = "center",
                            {win = "input", height = 1, border = "bottom"},
                            {win = "list", border = "none"},
                            {win = "preview", title = "{preview}", width = 0.6, height = 0.4, border = "top"},
                        },
                    },
                    telescope = {
                        reverse = true,
                        layout = {
                            box = "horizontal",
                            backdrop = false,
                            width = 0.8,
                            height = 0.9,
                            border = "none",
                            {
                                box = "vertical",
                                {win = "list", title = " Results ", title_pos = "center", border = "rounded"},
                                {win = "input", height = 1, border = "rounded", title = "{title} {live} {flags}", title_pos = "center"},
                            },
                            {
                                win = "preview",
                                title = "{preview:Preview}",
                                width = 0.50,
                                border = "rounded",
                                title_pos = "center",
                            },
                        },
                    },
                    ivy = {
                        layout = {
                            box = "vertical",
                            backdrop = false,
                            width = 0,
                            height = 0.4,
                            position = "bottom",
                            border = "top",
                            title = " {title} {live} {flags}",
                            title_pos = "left",
                            {win = "input", height = 1, border = "bottom"},
                            {
                                box = "horizontal",
                                {win = "list", border = "none"},
                                {win = "preview", title = "{preview}", width = 0.5, border = "left"},
                            },
                        },
                    },
                },
            },
            dashboard = {
                enabled = true,
                sections = {
                    { section = "header" }
                },
            },
        },
        keys = {
            {"<leader>lg", function() require("snacks").lazygit() end, desc = "Lazygit"},
            {"<leader>gl", function() require("snacks").lazygit.log() end, desc = "lazygit logs"},
            -- {"<leader>ee", function() require("snacks").explorer() end, desc = "snacks explorer"},
            {"<leader>pf", function() require("snacks").picker.files() end, desc = "snacks picker find files"},
            {"<leader>ps", function() require("snacks").picker.grep() end, desc = "grep word"},
        },
    }
}
