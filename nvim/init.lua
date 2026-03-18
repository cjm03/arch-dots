vim.opt.termguicolors = true
vim.opt.background = "dark"
-- vim.cmd.colorscheme("habamax")

-- =====================================
-- OPTIONS
-- =====================================
vim.opt.number = true
vim.opt.relativenumber = false
vim.opt.cursorline = true
vim.opt.cursorlineopt = "number"
vim.opt.wrap = false
vim.opt.scrolloff = 20

vim.opt.tabstop = 4
vim.opt.shiftwidth = 4
vim.opt.softtabstop = 4
vim.opt.expandtab = true
vim.opt.smartindent = true
vim.opt.autoindent = true

vim.opt.ignorecase = true
vim.opt.smartcase = true
vim.opt.hlsearch = false
vim.opt.incsearch = true

vim.opt.signcolumn = "auto"
vim.opt.cmdheight = 1
vim.opt.completeopt = "menuone,noselect,preview"
vim.opt.showmode = false
vim.opt.pumheight = 10
vim.opt.pumblend = 10
-- vim.opt.conceallevel = 0
-- vim.opt.concealcursor = ""
-- vim.opt.fillchars = { eob = " " }
vim.opt.lazyredraw = true
vim.opt.synmaxcol = 300

local undodir = vim.fn.expand("~/.vim/undodir")
if
	vim.fn.isdirectory(undodir) == 0
then
	vim.fn.mkdir(undodir, "p")
end

vim.opt.backup = false
vim.opt.writebackup = false
vim.opt.swapfile = false
vim.opt.undofile = true
vim.opt.undodir = undodir
vim.opt.updatetime = 300
vim.opt.timeoutlen = 500
vim.opt.ttimeoutlen = 0
vim.opt.autoread = true
vim.opt.autowrite = false

vim.opt.hidden = true
vim.opt.errorbells = false
vim.opt.backspace = "indent,eol,start"
vim.opt.autochdir = false
vim.opt.iskeyword:append("-")
vim.opt.path:append("**")
vim.opt.selection = "inclusive"
vim.opt.mouse = "a"
vim.opt.clipboard:append("unnamedplus")
vim.opt.modifiable = true
vim.opt.encoding = "UTF-8"

vim.opt.guicursor = ""

vim.opt.splitbelow = true
vim.opt.splitright = true

vim.opt.wildmenu = true
vim.opt.wildmode = "longest:full,full"
vim.opt.diffopt:append("linematch:60")
vim.opt.redrawtime = 10000
vim.opt.maxmempattern = 20000

-- ========================
-- KEYMAPS
-- ========================
vim.g.mapleader = " "
vim.g.maplocalleader = " "

vim.keymap.set("n", "n", "nzzzv")
vim.keymap.set("n", "N", "Nzzzv")
vim.keymap.set("i", "jk", "<ESC>")
vim.keymap.set("n", "<leader>w", ":w<CR>")

vim.keymap.set("n", "<leader>to", "<cmd>tabnew<CR>")
vim.keymap.set("n", "<leader>tx", "<cmd>tabclose<CR>")
vim.keymap.set("n", "<leader>tn", "<cmd>tabn<CR>")
vim.keymap.set("n", "<leader>tp", "<cmd>tabp<CR>")

vim.keymap.set("n", "<leader>sv", ":vsplit<CR>", { desc = "Split window vertically" })
vim.keymap.set("n", "<leader>sh", ":split<CR>", { desc = "Split window horizontally" })

vim.keymap.set("v", "<", "<gv", { desc = "Indent left and reselect" })
vim.keymap.set("v", ">", ">gv", { desc = "Indent right and reselect" })

vim.keymap.set("n", "C-h", ":TmuxNavigateLeft<CR>")
vim.keymap.set("n", "C-j", ":TmuxNavigateDown<CR>")
vim.keymap.set("n", "C-k", ":TmuxNavigateUp<CR>")
vim.keymap.set("n", "C-l", ":TmuxNavigateRight<CR>")

vim.keymap.set("n", "<leader>pa", function()
    local path = vim.fn.expand("%:p")
    vim.fn.setreg("+", path)
    print("file:", path)
end, { desc = "Copy full file path" })

vim.keymap.set("n", "<leader>td", function()
    vim.diagnostic.enable(not vim.diagnostic.is_enabled())
end, { desc = "Toggle diagnostics off/on" })

-- ================================================
-- AUTOCMDS
-- ================================================
local augroup = vim.api.nvim_create_augroup("UserConfig", { clear = true })

vim.api.nvim_create_autocmd("TextYankPost", {
    group = augroup,
    callback = function()
        vim.hl.on_yank()
    end,
})

-- ==========================
-- PLUGINS (vim.pack)
-- ==========================
vim.pack.add({
    "https://www.github.com/nvim-mini/mini.nvim",
    "https://www.github.com/lukas-reineke/indent-blankline.nvim",
    {
        src = "https://github.com/nvim-treesitter/nvim-treesitter",
        branch = "main",
        build = ":TSUpdate",
    },
    "https://www.github.com/neovim/nvim-lspconfig",
    "https://www.github.com/mason-org/mason.nvim",
    "https://www.github.com/creativenull/efmls-configs-nvim",
    "https://www.github.com/nvim-lualine/lualine.nvim",
    "https://www.github.com/stevearc/oil.nvim",
    "https://www.github.com/catgoose/nvim-colorizer.lua",
    "https://www.github.com/uhs-robert/oasis.nvim",
    {
        src = "https://www.github.com/saghen/blink.cmp",
        version = vim.version.range("1.*"),
    },
    "https://www.github.com/L3MON4D3/LuaSnip",
    "https://www.github.com/christoomey/vim-tmux-navigator",
})

local function packadd(name)
    vim.cmd("packadd " .. name)
end
packadd("mini.nvim")
packadd("indent-blankline.nvim")
packadd("nvim-treesitter")
packadd("nvim-lspconfig")
packadd("mason.nvim")
packadd("efmls-configs-nvim")
packadd("lualine.nvim")
packadd("oil.nvim")
packadd("nvim-colorizer.lua")
packadd("oasis.nvim")
packadd("blink.cmp")
packadd("LuaSnip")
packadd("vim-tmux-navigator")




-- =========================
-- PLUGIN CONFIGS
-- =========================

-------------------------------------------------- mini.nvim
local win_config = function()
    local height = math.floor(0.618 * vim.o.lines)
    local width = math.floor(0.618 * vim.o.columns)
    return {
        anchor = 'NW', height = height, width = width,
        row = math.floor(0.5 * (vim.o.lines - height)),
        col = math.floor(0.5 * (vim.o.columns - width)),
    }
end

require("mini.icons").setup({})
require("mini.pick").setup({
    window = { config = win_config }
})

vim.keymap.set("n", "<leader>f", "<cmd>Pick files<CR>")
vim.keymap.set("n", "<leader>r", "<cmd>Pick buffers<CR>")
vim.keymap.set("n", "<leader>h", "<cmd>Pick help<CR>")

-------------------------------------------------- indent-blankline
require("ibl").setup({
    indent = { char = "│" },
})

-------------------------------------------------- treesitter
local setup_treesitter = function()
    local treesitter = require("nvim-treesitter")
    treesitter.setup({})
    local ensure_installed = {
        "vim",
        "vimdoc",
        "c",
        "cpp",
        "rust",
        "html",
        "css",
        "json",
        "lua",
        "markdown",
        "python",
        "bash",
        "fish",
        "gitignore",
        "make",
        "cmake",
        "python",
    }

    local config = require("nvim-treesitter.config")
    local already_installed = config.get_installed()
    local parsers_to_install = {}
    for _, parser in ipairs(ensure_installed) do
        if not vim.tbl_contains(already_installed, parser) then
            table.insert(parsers_to_install, parser)
        end
    end
    if #parsers_to_install > 0 then
        treesitter.install(parsers_to_install)
    end
    local group = vim.api.nvim_create_augroup("TreeSitterConfig", { clear = true})
    vim.api.nvim_create_autocmd("FileType", {
        group = group,
        callback = function(args)
            if vim.list_contains(treesitter.get_installed(), vim.treesitter.language.get_lang(args.match)) then
                vim.treesitter.start(args.buf)
            end
        end,
    })
end
setup_treesitter()

-------------------------------------------------- mason.nvim
require("mason").setup({})
local diagnostic_signs = {
	Error = "",
	Warn = "",
	Hint = "",
	Info = "",
}
vim.diagnostic.config({
    virtual_text = { prefix = "●", spacing = 4 },
    signs = {
        text = {
            [vim.diagnostic.severity.ERROR] = diagnostic_signs.Error,
            [vim.diagnostic.severity.WARN] = diagnostic_signs.Warn,
            [vim.diagnostic.severity.INFO] = diagnostic_signs.Info,
            [vim.diagnostic.severity.HINT] = diagnostic_signs.Hint,
        },
    },
    underline = true,
    update_in_insert = false,
    severity_sort = true,
    float = {
        border = "rounded",
        source = "always",
        header = "",
        prefix = "",
        focusable = false,
        style = "minimal",
    },
})

do
    local orig = vim.lsp.util.open_floating_preview
    function vim.lsp.util.open_floating_preview(contents, syntax, opts, ...)
        opts = opts or {}
        opts.border = opts.border or "rounded"
        return orig(contents, syntax, opts, ...)
    end
end

local function lsp_on_attach(ev)
    local client = vim.lsp.get_client_by_id(ev.data.client_id)
    if not client then
        return
    end

    local bufnr = ev.buf
    local opts = { noremap = true, silent = true, buffer = bufnr }

    vim.keymap.set("n", "<leader>gd", vim.lsp.buf.definition, opts)

    vim.keymap.set("n", "<leader>gD", function()
        require("fzf-lua").lsp_definitions({ jump_to_single_result = true })
    end, opts)

    vim.keymap.set("n", "<leader>ca", vim.lsp.buf.code_action, opts)
    vim.keymap.set("n", "K", vim.lsp.buf.hover, opts)

    vim.keymap.set("n", "<leader>go", function()
        vim.diagnostic.open_float({ scope = "line" })
    end, opts)

    vim.keymap.set("n", "<leader>gO", function()
        vim.diagnostic.open_float({ scope = "cursor" })
    end, opts)

    if client:supports_method("textDocument/codeAction", bufnr) then
        vim.keymap.set("n", "<leader>oi", function()
            vim.lsp.buf.code_action({
                context = { only = { "source.organizeImports" }, diagnostics = {} },
                apply = true,
                bufnr = bufnr,
            })
            vim.defer_fn(function()
                vim.lsp.buf.format({ bufnr = bufnr })
            end, 50)
        end, opts)
    end
end

vim.api.nvim_create_autocmd("LspAttach", { group = augroup, callback = lsp_on_attach })

require("blink.cmp").setup({
    keymap = {
        preset = "none",
        ["<C-e>"] = { "cancel" },
        ["<CR>"] = { "accept", "fallback" },
        ["<Up>"] = { "select_prev", "fallback" },
        ["<Down>"] = { "select_next", "fallback" },
    },
    appearance = { nerd_font_variant = "mono" },
    completion = { menu = { auto_show = true } },
    sources = { default = { "lsp", "path", "buffer", "snippets" } },
    snippets = {
        expand = function(snippet)
            require("luasnip").lsp_expand(snippet)
        end,
    },

    fuzzy = {
        implementation = "prefer_rust",
        prebuilt_binaries = { download = true },
    },
})

vim.lsp.config["*"] = {
    capabilities = require("blink.cmp").get_lsp_capabilities(),
}

vim.lsp.config("lua_ls", {
    settings = {
        Lua = {
            diagnostics = { globals = { "vim" } },
            telemetry = { enable = false },
        },
    },
})
vim.lsp.config("pyright", {})
vim.lsp.config("bashls", {})
vim.lsp.config("clangd", {})
vim.lsp.config("html", {})

do
    local luacheck = require("efmls-configs.linters.luacheck")
    local stylua = require("efmls-configs.formatters.stylua")
    local flake8 = require("efmls-configs.linters.flake8")
    local black = require("efmls-configs.formatters.black")
    local prettier_d = require("efmls-configs.formatters.prettier_d")
    local fixjson = require("efmls-configs.formatters.fixjson")
    local shellcheck = require("efmls-configs.linters.shellcheck")
    local shfmt = require("efmls-configs.formatters.shfmt")
    -- local cpplint = require("efmls-configs.linters.cpplint")
    -- local clangfmt = require("efmls-configs.linters.clang_format")
    local gcc = require("efmls-configs.linters.gcc")
    local cmake_lint = require("efmls-configs.linters.cmake_lint")
    local checkmake = require("efmls-configs.linters.checkmake")

    vim.lsp.config("efm", {
        filetypes = {
            "c",
            "cpp",
            "css",
            "html",
            "json",
            "jsonc",
            "lua",
            "python",
            "markdown",
            "sh",
            "cmake",
            "make",
        },
        init_options = { documentFormatting = true },
        settings = {
            languages = {
                c = { gcc },
                cpp = { gcc },
                css = { prettier_d },
                html = { prettier_d },
                json = { fixjson },
                jsonc = { fixjson },
                lua = { luacheck, stylua },
                markdown = { prettier_d },
                python = { flake8, black },
                sh = { shellcheck, shfmt },
                cmake = { cmake_lint },
                make = { checkmake },
            },
        },
    })
end

vim.lsp.enable({
    "lua_ls",
    "pyright",
    "bashls",
    "clangd",
    "html",
    "efm",
})

-------------------------------------------------- lualine
require("lualine").setup({
    options = {
        theme = "oasis",
        global_status = false,
        section_separators = "",
        component_separators = "",
    },
})

-------------------------------------------------- oil
require("oil").setup({
    default_file_explorer = true,
    columns = { "icon", "permissions", "size", "mtime" },
    keymaps = {
        ["<C-h>"] = false,
        ["<C-c>"] = false,
        ["<M-h>"] = "actions.select_split",
        ["q"] = "actions.close",
    },
    delete_to_trash = true,
    view_options = { show_hidden = true, },
    skip_confirm_for_simple_edits = true,
})
vim.keymap.set("n", "-", "<CMD>Oil<CR>", { desc = "oil nonfloat currentdir" })
vim.keymap.set("n", "<leader>-", "<CMD>Oil /home/crab/<CR>", { desc = "oil nonfloat $HOME" })
vim.api.nvim_create_autocmd("FileType", {
    pattern = "oil",
    callback = function()
        vim.opt_local.cursorline = false
    end,
})

-------------------------------------------------- colorizer
require("colorizer").setup({
    user_default_options = { suppress_deprecation = true, }
})

-------------------------------------------------- oasis
require("oasis").setup({
    style = "starlight",
    styles = { italic = false, },
})
vim.cmd.colorscheme("oasis")

-- ====================================
-- FLOATING TERMINAL
-- ====================================
vim.api.nvim_create_autocmd("TermClose", {
    group = augroup,
    callback = function()
        if vim.v.event.status == 0 then
            vim.api.nvim_buf_delete(0, {})
        end
    end,
})

vim.api.nvim_create_autocmd("TermOpen", {
    group = augroup,
    callback = function()
        vim.opt_local.number = false
        vim.opt_local.relativenumber = false
        vim.opt_local.signcolumn = "no"
    end,
})

local terminal_state = { buf = nil, win = nil, is_open = false }

local function FloatingTerminal()
    if terminal_state.is_open and terminal_state.win and vim.api.nvim_win_is_valid(terminal_state.win) then
        vim.api.nvim_win_close(terminal_state.win, false)
        terminal_state.is_open = false
        return
    end

    if not terminal_state.buf or not vim.api.nvim_buf_is_valid(terminal_state.buf) then
        terminal_state.buf = vim.api.nvim_create_buf(false, true)
        vim.bo[terminal_state.buf].bufhidden = "hide"
    end

    local width = math.floor(vim.o.columns * 0.8)
    local height = math.floor(vim.o.lines * 0.8)
    local row = math.floor((vim.o.lines - height) / 2)
    local col = math.floor((vim.o.columns - width) / 2)

    terminal_state.win = vim.api.nvim_open_win(terminal_state.buf, true, {
        relative = "editor",
        width = width,
        height = height,
        row = row,
        col = col,
        style = "minimal",
        border = "rounded",
    })

    vim.wo[terminal_state.win].winblend = 0
    vim.wo[terminal_state.win].winhighlight = "Normal:FloatingTermNormal,FloatBorder:FloatingTermBorder"
    vim.api.nvim_set_hl(0, "FloatingTermNormal", { bg = "none" })
    vim.api.nvim_set_hl(0, "FloatingTermBorder", { bg = "none" })

    local has_terminal = false
    local lines = vim.api.nvim_buf_get_lines(terminal_state.buf, 0, -1, false)
    for _, line in ipairs(lines) do
        if line ~= "" then
            has_terminal = true
            break
        end
    end
    if not has_terminal then
        vim.fn.termopen(os.getenv("SHELL"))
    end

    terminal_state.is_open = true
    vim.cmd("startinsert")

    vim.api.nvim_create_autocmd("BufLeave", {
        buffer = terminal_state.buf,
        callback = function()
            if terminal_state.is_open and terminal_state.win and vim.api.nvim_win_is_valid(terminal_state.win) then
                vim.api.nvim_win_close(terminal_state.win, false)
                terminal_state.is_open = false
            end
        end,
        once = true,
    })
end

vim.keymap.set("n", "<leader>t", FloatingTerminal, { noremap = true, silent = true, desc = "Toggle floating terminal" })
vim.keymap.set("t", "<Esc>", function()
    if terminal_state.is_open and terminal_state.win and vim.api.nvim_win_is_valid(terminal_state.win) then
        vim.api.nvim_win_close(terminal_state.win, false)
        terminal_state.is_open = false
    end
end, { noremap = true, silent = true, desc = "Close floating terminal" })
















