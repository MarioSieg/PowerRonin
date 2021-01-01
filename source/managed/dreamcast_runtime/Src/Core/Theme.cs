using Dreamcast.Mathematics;

namespace Dreamcast.Core
{
    /// <summary>
    /// Contains all colors for the editor theme.
    /// </summary>
    public sealed class Theme
    {
        public Color4 Text { get; set; } = new Color4();
        public Color4 TextDisabled { get; set; } = new Color4();
        public Color4 WindowBackground { get; set; } = new Color4();
        public Color4 ChildBackground { get; set; } = new Color4();
        public Color4 PopupBackground { get; set; } = new Color4();
        public Color4 Border { get; set; } = new Color4();
        public Color4 BorderShadow { get; set; } = new Color4();
        public Color4 FrameBackground{ get; set; } = new Color4();
        public Color4 FrameBackgroundHovered { get; set; } = new Color4();
        public Color4 FrameBackgroundActive { get; set; } = new Color4();
        public Color4 TitleBackground { get; set; } = new Color4();
        public Color4 TitleBackgroundActive { get; set; } = new Color4();
        public Color4 TitleBackgroundCollapsed { get; set; } = new Color4();
        public Color4 MenuBarBackground { get; set; } = new Color4();
        public Color4 ScrollBarBackground { get; set; } = new Color4();
        public Color4 ScrollBarGrab { get; set; } = new Color4();
        public Color4 ScrollBarGrabHovered{ get; set; } = new Color4();
        public Color4 ScrollBarGrabActive { get; set; } = new Color4();
        public Color4 CheckMark { get; set; } = new Color4();
        public Color4 SliderGrab { get; set; } = new Color4();
        public Color4 SliderGrabActive { get; set; } = new Color4();
        public Color4 Button { get; set; } = new Color4();
        public Color4 ButtonHovered { get; set; } = new Color4();
        public Color4 ButtonActive { get; set; } = new Color4();
        public Color4 Header { get; set; } = new Color4();
        public Color4 HeaderHovered { get; set; } = new Color4();
        public Color4 HeaderActive { get; set; } = new Color4();
        public Color4 Separator { get; set; } = new Color4();
        public Color4 SeparatorHovered { get; set; } = new Color4();
        public Color4 SeparatorActive { get; set; } = new Color4();
        public Color4 ResizeGrip { get; set; } = new Color4();
        public Color4 ResizeGripHovered { get; set; } = new Color4();
        public Color4 ResizeGripActive { get; set; } = new Color4();
        public Color4 Tab { get; set; } = new Color4();
        public Color4 TabHovered { get; set; } = new Color4();
        public Color4 TabActive { get; set; } = new Color4();
        public Color4 TabUnfocused { get; set; } = new Color4();
        public Color4 TabUnfocusedActive { get; set; } = new Color4();
        public Color4 PlotLines { get; set; } = new Color4();
        public Color4 PlotLinesHovered { get; set; } = new Color4();
        public Color4 PlotHistogram { get; set; } = new Color4();
        public Color4 PlotHistogramHovered { get; set; } = new Color4();
        public Color4 TextSelectedBackground { get; set; } = new Color4();
        public Color4 DragDropTarget { get; set; } = new Color4();
        public Color4 NavHighlight { get; set; } = new Color4();
        public Color4 NavWindowingHighlight { get; set; } = new Color4();
        public Color4 NavWindowingDimBackground { get; set; } = new Color4();
        public Color4 ModalWindowDimBackground { get; set; } = new Color4();
    }
}
