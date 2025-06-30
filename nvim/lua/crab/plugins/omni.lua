return {
    "sylvanfranklin/omni-preview.nvim",
    dependencies = {
        { 'toppair/peek.nvim', lazy = true, build = "deno task --quiet build:fast" },
        { 'chomosuke/typst-preview.nvim', lazy = true },
    },
    config = function()
        require("omni-preview").setup()
        require("typst-preview").setup({
            dependencies_bin = {
                ['tinymist'] = "/usr/bin/tinymist",
            },
        })
        require("peek").setup({ app = "browser" })
        vim.keymap.set("n", "<leader>po", ":OmniPreview start<CR>", { silent = true })
        vim.keymap.set("n", "<leader>px", ":OmniPreview stop<CR>", { silent = true })
    end
}
