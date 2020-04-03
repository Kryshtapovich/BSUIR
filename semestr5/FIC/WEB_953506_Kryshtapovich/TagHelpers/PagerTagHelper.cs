using Microsoft.AspNetCore.Mvc.Rendering;
using Microsoft.AspNetCore.Razor.TagHelpers;
using Microsoft.AspNetCore.Routing;

namespace WEB_953506_Kryshtapovich.TagHelpers
{
    public class PagerTagHelper : TagHelper
    {
        private LinkGenerator linkGenerator;
        public int PageCurrent { get; set; }
        public int PageTotal { get; set; }
        public string PagerClass { get; set; }
        public string Action { get; set; }
        public string Controller { get; set; }
        public int? ClassId { get; set; }

        public PagerTagHelper(LinkGenerator linkGenerator)
        {
            this.linkGenerator = linkGenerator;
        }

        public override void Process(TagHelperContext context, TagHelperOutput output)
        {
            output.TagName = "nav";

            var ulTag = new TagBuilder("ul");
            ulTag.AddCssClass("pagination");
            ulTag.AddCssClass(PagerClass);

            for (int i = 1; i <= PageTotal; i++)
            {
                var url = linkGenerator.GetPathByAction(Action, Controller,
                new
                {
                    page = i,
                    carClass = ClassId == 0 ? null : ClassId
                }
                );
                var item = GetPagerItem(url, i.ToString(), i == PageCurrent, i == PageCurrent);
                ulTag.InnerHtml.AppendHtml(item);
            }
            output.Content.AppendHtml(ulTag);
        }

        private TagBuilder GetPagerItem(string url, string text, bool active = false, bool disabled = false)
        {

            var liTag = new TagBuilder("li");
            liTag.AddCssClass("page-item");
            liTag.AddCssClass(active ? "active" : "");

            var aTag = new TagBuilder("a");
            aTag.AddCssClass("page-link");
            aTag.Attributes.Add("href", url);
            aTag.InnerHtml.Append(text);

            liTag.InnerHtml.AppendHtml(aTag);
            return liTag;
        }
    }
}