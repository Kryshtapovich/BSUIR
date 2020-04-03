import "./index.scss";

import cx from "classnames";
import { SyntheticEvent, useEffect, useState } from "react";

interface RouteProps {
  path: string;
  component: () => JSX.Element;
}

export function Route(props: RouteProps) {
  const { path, component } = props;
  const [currentPath, setCurrentPath] = useState(location.pathname);

  const locationChange = () => setCurrentPath(location.pathname);

  useEffect(() => {
    window.addEventListener("popstate", locationChange);
    return () => window.removeEventListener("popstate", locationChange);
  }, []);

  return currentPath === path ? component() : null;
}

interface NavLinkProps {
  path: string;
  content: string;
  className?: string;
}

export function NavLink(props: NavLinkProps) {
  const { path, content, className } = props;

  const handleClick = (e: SyntheticEvent) => {
    e.preventDefault();
    history.pushState({}, "", path);
    window.dispatchEvent(new PopStateEvent("popstate"));
  };

  const classes = cx("nav-link", {
    [className as string]: className
  });

  return (
    <a href={path} className={classes} onClick={handleClick}>
      {content}
    </a>
  );
}
