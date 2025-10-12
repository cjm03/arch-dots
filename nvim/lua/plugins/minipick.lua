return {
    "nvim-mini/mini.pick",
    version = "*",
    dependencies = { "nvim-mini/mini.icons", },
    config = function()
        require("mini.pick").setup({})
    end
}
