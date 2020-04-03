using Microsoft.AspNetCore.Razor.TagHelpers;
using Microsoft.AspNetCore.Routing;

namespace WEB_953506_Kryshtapovich.TagHelpers
{
    [HtmlTargetElement(tag: "img", Attributes = "img-action, img-controller")]
    public class ImageTagHelper : TagHelper
    {
        private LinkGenerator linkGenerator;
        public string ImgAction { get; set; }
        public string ImgController { get; set; }
        
        public ImageTagHelper(LinkGenerator linkGenerator)
        {
            this.linkGenerator = linkGenerator;
        }

        public override void Process(TagHelperContext context, TagHelperOutput output)
        {
            var uri = linkGenerator.GetPathByAction(ImgAction, ImgController);
            output.Attributes.Add("src", uri);
        }
    }
}